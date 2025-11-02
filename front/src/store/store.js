import { configureStore } from '@reduxjs/toolkit'
import { routeReducer } from './routeSlice'
import { historyReducer } from './historySlice'
import { inputReducer } from './inputSlice'

export const store = configureStore({
  reducer: {
    route: routeReducer,
    history: historyReducer,
    input: inputReducer
  },
})