import { API_ROUTES } from "../constants/api-routes.js"
import { mathServer } from "./instance.js"

export const primeTest = async (number, iterations) => {
    return await mathServer.post(`/${API_ROUTES.prime_test}`, {
        iterations,
        number
    })
}