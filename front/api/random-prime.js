import { API_ROUTES } from "../constants/api-routes.js"
import { mathServer } from "./instance.js"

export const randomPrime = async () => {
    return await mathServer.post(`/random_prime`, {})
}