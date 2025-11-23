import { API_ROUTES } from "./api-routes"

const clientRoutes = [
    {
        routes: [
            {
                name: 'Система довгої модульної арифметики',
                slug: 'main'
            }
        ]
    },
    {
        section: 'Скінченне поле чисел',
        routes: [
            {
                name: 'Арифметичні операції у скінченному полі',
                slug: API_ROUTES.finite_field
            },
            {
                name: 'Розклад числа на множники',
                slug: API_ROUTES.number_factorization
            },
            {
                name: 'Знаходження порядку числа',
                slug: API_ROUTES.number_order
            },
            {
                name: 'Ймовірнісна перевірка числа на простоту',
                slug: API_ROUTES.prime_test,
            }
        ]
    },
]

export const CLIENT_ROUTES = Object.freeze(clientRoutes)