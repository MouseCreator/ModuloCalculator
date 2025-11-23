import axios from "axios";

export const mathServer = axios.create({
    baseURL: 'http://localhost:8080/S/',
})

mathServer.interceptors.response.use(res => {
    const resDat = res.data.data
    if(resDat instanceof Object){
        res.data = resDat.result
    } else {
        res.data = resDat
    }
    return res
}, err => {
    throw new Error(err.response.data.error)
})

mathServer.interceptors.request.use(req => {
    req.headers["Content-Type"] = 'application/json'
    return req
})