(ns common.payment
  (:require [clojure.string :as s]
            [clj-http.client :as client]
            [common.config :as config]
            [common.util :refer [only-prod send-email]]))

;; We are using Stripe API version 2015-01-26

(def common-opts
  {:basic-auth config/stripe-private-key
   :as :json
   :coerce :always
   :throw-exceptions false})

(defn stripe-req
  [method endpoint & [params headers]]
  (try (let [opts (merge-with merge 
                              common-opts
                              {:form-params params}
                              {:headers headers})
             resp (:body ((resolve (symbol "clj-http.client" method))
                          (str config/stripe-api-url endpoint)
                          opts))]
         {:success (not (:error resp))
          :resp resp})
       (catch Exception e
         {:success false
          :resp {:error {:message "Unknown error."}}})))

(defn create-stripe-customer
  [user-id stripe-token]
  (stripe-req "post"
              "customers"
              {:description (str "Purple ID: " user-id)
               :card stripe-token}))

(defn get-stripe-customer
  [customer-id]
  (stripe-req "get" (str "customers/" customer-id)))

(defn add-stripe-card
  [customer-id stripe-token]
  (stripe-req "post"
              (str "customers/" customer-id "/cards")
              {:card stripe-token}))

(defn delete-stripe-card
  [customer-id card-id]
  (stripe-req "delete"
              (str "customers/" customer-id "/cards/" card-id)))

(defn set-default-stripe-card
  [customer-id card-id]
  (stripe-req "post"
              (str "customers/" customer-id)
              {:default_card card-id}))

;; this should be refactored since it confuses by changing
;; the meaning of :success
(defn charge-stripe-customer
  "Authorize (and optionally capture) a charge on a Stripe customer object."
  [customer-id
   amount ;; in cents; stripe docs: min. amount is $0.50 US (TODO enforce this)
   description
   receipt-email
   capture
   idempotency-key
   metadata]
  (let [resp (:resp (stripe-req "post"
                                "charges"
                                {:customer customer-id
                                 :amount amount
                                 :capture capture
                                 :currency config/default-currency
                                 :description description
                                 :receipt_email receipt-email
                                 :metadata (or metadata {})}
                                {:Idempotency-Key idempotency-key}))]
    {:success (boolean (:paid resp))
     :charge resp}))

(defn capture-stripe-charge
  "Captures an authorized charge."
  [charge-id & {:keys [amount]}]
  (let [resp (:resp (stripe-req "post"
                                (str "charges/" charge-id "/capture")
                                (when amount {:amount amount})))]
    (if (:captured resp)
      {:success true
       :charge resp}
      (do (only-prod (send-email
                      {:to "chris@purpledelivery.com"
                       :subject "Failed Stripe Charge Capture"
                       :body (str "Failed charge capture details:\n\n"
                                  "Charge ID: " charge-id "\n")}))
          {:success false
           :charge resp}))))

(defn refund-stripe-charge
  "Refunds a Stripe charge. Use on auth'd charges whether or not captured."
  [charge-id]
  (let [resp (:resp (stripe-req "post" (str "charges/" charge-id "/refunds")))]
    (if (:id resp)
      {:success true
       :refund resp}
      (do (only-prod (send-email
                      {:to "chris@purpledelivery.com"
                       :subject "Failed Stripe Charge Refund"
                       :body (str "Failed charge refund details:\n\n"
                                  "Refund ID: " charge-id "\n")}))
          {:success false
           :refund resp}))))

(defn get-stripe-charge
  [charge-id]
  (stripe-req "get" (str "charges/" charge-id)))

(defn update-stripe-charge
  "Update a Stripe charge."
  [charge-id description]
  (let [resp (:resp (stripe-req "post"
                                (str "charges/" charge-id)
                                {:description description}))]
    (if (:id resp)
      {:success true}
      (do (only-prod (send-email
                      {:to "chris@purpledelivery.com"
                       :subject "Failed To Update Stripe Charge"
                       :body (str "Details:\n\n"
                                  "Charge ID: " charge-id "\n")}))
          {:success false
           :resp resp}))))