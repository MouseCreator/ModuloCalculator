import { Input } from '../input/input/Input'
import { TextField } from '../text-field/text-field/TextField.jsx'
import './Searchbar.css'
import { CLIENT_ROUTES } from '../../../constants/routes'
import { useNavigate } from '@tanstack/react-router'
import { useDispatch, useSelector } from 'react-redux'
import { setRoute } from '../../store/routeSlice'
import {useEffect} from "react";

export const Searchbar = () => {
    const dispatch = useDispatch()
    const location = useSelector((state) => state.route.value)
    const navigate = useNavigate()

    const navigator = (event, to) => {
        event.preventDefault()
        dispatch(setRoute(to))
        navigate({to: `/${to.slug}`})
    }

    useEffect(() => {
        navigate({to: `/main`})
    }, [navigate]);

    return <div className='searchbar component searchbar__style'>
        <div className='searchbar__search'>
            <Input placeholder='Пошук'/>
        </div>
        <div className='searchbar__list'>
            <ul>
            {
                CLIENT_ROUTES
                    .slice(1)
                    .map((group) => <>
                    <li key={group.section} className='list__section-name'><TextField>{group.section}</TextField></li>
                    <ul>
                        {
                            group.routes.map(route => <>
                                <li
                                    key={route.slug}
                                    className='list__route'
                                    style={{color: route.slug === location.slug ? 'white' : '#97afc7'}}
                                    onClick={(e) => navigator(e, route)}
                                >
                                    {route.name}
                                </li>
                            </>)
                        }
                    </ul>
                </>)
            }
            </ul>
        </div>
    </div>
}