import { API_ROUTES } from "../constants/api-routes.js"
import { mathServer } from "./instance.js"

export const numberOrder = async (number, n) => {
    return await mathServer.post(`/${API_ROUTES.number_order}`, {
        number,
        n: n ? n : "41",
    })
}