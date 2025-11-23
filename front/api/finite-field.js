import { API_ROUTES } from "../constants/api-routes.js"
import { mathServer } from "./instance.js"

export const finiteField = async (expr, n) => {
    return await mathServer.post(`/${API_ROUTES.finite_field}`, {
        expr,
        n: n ? n : 0,
    })
}