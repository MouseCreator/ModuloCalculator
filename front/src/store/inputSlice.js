import { createSlice } from '@reduxjs/toolkit'

export const inputSlice = createSlice({
    name: 'input',
    initialState: {
        firstInput: '',
        secondInput: '',
    },
    reducers: {
        setFirstInput: (state, action) => {
            state.firstInput = action.payload
        },
        setSecondInput: (state, action) => {
            state.secondInput = action.payload
        },
    },
})

export const { setFirstInput, setSecondInput } = inputSlice.actions
export const inputReducer = inputSlice.reducer
