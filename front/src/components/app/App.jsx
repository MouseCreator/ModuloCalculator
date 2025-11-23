import { Button } from '../button/button/Button.jsx'
import { Input } from '../input/input/Input'
import { TextField } from '../text-field/text-field/TextField'
import { MainTextField } from '../text-field/main-text-field/MainTextField'
import './App.css'
import { METHOD_MAP } from '../../../api/methods-map'
import { useSelector, useDispatch } from 'react-redux'
import { setFirstInput, setSecondInput } from '../../store/inputSlice'
import { useState, useRef, useEffect } from 'react'
import { MainButton } from "../button/main-button/MainButton.jsx"
import { useNavigate, useLocation  } from "@tanstack/react-router"
import { setRoute } from '../../store/routeSlice'
import { CLIENT_ROUTES } from "../../../constants/routes.js"
import { randomPrime } from '../../../api/random-prime'

export const App = () => {
    const route = useSelector(state => state.route.value)
    const handler = METHOD_MAP[route.slug]
    const dispatch = useDispatch()
    const navigate = useNavigate()
    const location = useLocation()

    const inputRef = useRef(null)
    const [inputValue, setInputValue] = useState('')
    const [secondInputValue, setSecondInputValue] = useState('')

    useEffect(() => {
        const currentRoute = CLIENT_ROUTES.flatMap((group) => group.routes).find(
            (r) => `/${r.slug}` === location.pathname
        )

        if (currentRoute && currentRoute.slug !== route.slug) {
            dispatch(setRoute(currentRoute))
        }
    }, [location, dispatch, route])

    const handleRPN = async () => {
        try {
            const result = await randomPrime()
            if (result?.data) {
                setSecondInputValue(result.data)
                dispatch(setSecondInput(result.data))
            } else {
                console.error('Error');
            }
        } catch (error) {
            console.error(error)
        }
    }

    const handleFirstInputChange = (event) => {
        const value = event.target.value
        setInputValue(value)
        dispatch(setFirstInput(value))
    }

    const handleSecondInputChange = (event) => {
        const value = event.target.value
        setSecondInputValue(value)
        dispatch(setSecondInput(value))
    }

    const navigateToCalculator = () => {
        const calculatorRoute = CLIENT_ROUTES
            .flatMap(group => group.routes)
            .find(route => route.name === 'Арифметичні операції у скінченному полі')

        if (calculatorRoute) {
            dispatch(setRoute(calculatorRoute))
            navigate({ to: `/${calculatorRoute.slug}` })
        } else {
            console.error('Error')
        }
    }

    const openUserGuide = () => {
        const userGuideUrl = 'https://github.com/MouseCreator/ModuloCalculator/blob/main/README.md'
        window.open(userGuideUrl, '_blank')
    }

    const insertText = (text) => {
        const input = inputRef.current;
        if (input) {
            const start = input.selectionStart;
            const end = input.selectionEnd;

            const newValue =
                inputValue.slice(0, start) + text + inputValue.slice(end);

            setInputValue(newValue);

            let cursorPosition = start + text.length;
            if (text.includes("()")) {
                cursorPosition = start + text.indexOf("()") + 1;
            }

            setTimeout(() => {
                input.setSelectionRange(cursorPosition, cursorPosition);
                input.focus();
            }, 0);
        }
    }

    const handleButtonClick = (event) => {
        const buttonText = event.target.textContent;
        insertText(buttonText);
    }

    return <div className="app component app__style">
        {route?.slug === 'main' && (
            <>
                <div className="main-app__main-box">
                    <MainTextField>
                        Система довгої модульної арифметики – це веб-застосунок
                        для здійснення математичних операцій над скінченними полями, дійсними
                        числами та кільцем многочленів. Він підтримує широкий спектр операцій,
                        включаючи додавання, віднімання, множення, ділення та обчислення обернених
                        значень. Застосунок дозволяє ефективно обчислювати великі числа, що робить
                        його ідеальним інструментом для використання в криптографії та теорії чисел.
                        Основні користувачі – це студенти, викладачі, інженери та науковці, які
                        працюють у сферах комп'ютерних наук, прикладної математики та кібербезпеки.
                    </MainTextField>
                </div>

                <div className="main-app__buttons">
                    <MainButton onClick={navigateToCalculator}>• до калькулятора</MainButton>
                    <MainButton onClick={openUserGuide}>• настанова користувача</MainButton>
                </div>
            </>
        )}

        {route?.slug !== 'main' && (
            <div className="app__main-box">
                <TextField>Поле для вводу арифметичних виразів:</TextField>
                <Input
                    ref={inputRef}
                    placeholder='First input'
                    value={inputValue}
                    onChange={handleFirstInputChange}
                />
            </div>
        )}
        {route?.slug === 'finite_field' && (
            <div className="app__fucntion-buttons">
                <Button onClick={handleButtonClick}>sqrt()</Button>
                <Button onClick={handleButtonClick}>+</Button>
                <Button onClick={handleButtonClick}>*</Button>
                <Button onClick={handleButtonClick}>log()</Button>
                <Button onClick={handleButtonClick}>-</Button>
                <Button onClick={handleButtonClick}>/</Button>
                <Button onClick={handleButtonClick}>eul()</Button>
                <Button onClick={handleButtonClick}>(</Button>
                <Button onClick={handleButtonClick}>)</Button>
                <Button onClick={handleButtonClick}>kar()</Button>
                <Button onClick={handleButtonClick}>^</Button>
            </div>
        )}
        {(route?.slug === 'finite_field' || route?.slug === 'number_order') && (
            <div className="app__random-box">
                <div className='app__random-box__text-container'>
                    <TextField>Розмір поля:</TextField>
                </div>
                <Button onClick={handleRPN}>RPN</Button>
                <Input
                    placeholder='Second input'
                    value={secondInputValue}
                    onChange={handleSecondInputChange}
                />
            </div>
        )}

        {route?.slug === 'prime_test' && (
            <div className="app__box">
                <div className='app__random-box__text-container'>
                    <TextField>К-сть ітерацій:</TextField>
                </div>
                <Input
                    placeholder='0000'
                    value={secondInputValue}
                    onChange={handleSecondInputChange}
                />
            </div>
        )}
    </div>
}