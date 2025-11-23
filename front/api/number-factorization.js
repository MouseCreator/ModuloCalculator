import { API_ROUTES } from "../constants/api-routes.js"
import { mathServer } from "./instance.js"

export const numberFactorization = async (n) => {
    return await mathServer.post(`/${API_ROUTES.number_factorization}`, {
        n
    })
}