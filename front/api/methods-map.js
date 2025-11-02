import { API_ROUTES } from "../constants/api-routes";
import { finiteField } from "./finite-field";
import { numberFactorization } from "./number-factorization";
import { numberOrder } from "./number-order";
import { primeTest } from "./prime-test";

const methodMap = {
    [API_ROUTES.finite_field]: finiteField,
    [API_ROUTES.number_factorization]: numberFactorization,
    [API_ROUTES.number_order]: numberOrder,
    [API_ROUTES.prime_test]: primeTest
}

export const METHOD_MAP = Object.freeze(methodMap)