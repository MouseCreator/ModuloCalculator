import { createSlice } from "@reduxjs/toolkit";
import { CLIENT_ROUTES } from "../../constants/routes";

export const initialState = {
    value: CLIENT_ROUTES[0].routes[0]
}

export const routeSlice = createSlice({
    name: 'route',
    initialState,
    reducers: {
        setRoute: (state, action) => {
            state.value = action.payload
        }
    }
})

export const { setRoute } = routeSlice.actions
export const routeReducer = routeSlice.reducer