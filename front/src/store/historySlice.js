import { createSlice } from '@reduxjs/toolkit'

export const historySlice = createSlice({
    name: 'history',
    initialState: {
        log: []
    },
    reducers: {
        addResult: (state, action) => {
            state.log.push(action.payload)
        },
        clearHistory: (state) => {
            state.log = []
        }
    }
})

export const { addResult, clearHistory } = historySlice.actions
export const historyReducer = historySlice.reducer
