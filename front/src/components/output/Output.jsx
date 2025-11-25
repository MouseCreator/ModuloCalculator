import { useSelector, useDispatch } from 'react-redux'
import { Button } from '../button/button/Button.jsx'
import { OutputField } from '../input/output/OutputField'
import { TextField } from '../text-field/text-field/TextField.jsx'
import './Output.css'
import { METHOD_MAP } from '../../../api/methods-map'
import { useState } from 'react'
import { addResult } from '../../store/historySlice'

export const Output = () => {
    const route = useSelector(state => state.route.value)
    const handler = METHOD_MAP[route.slug]
    const dispatch = useDispatch()
    const firstInput = useSelector((state) => state.input.firstInput)
    const secondInput = useSelector((state) => state.input.secondInput)
    const [output, setOutput] = useState('')

    const onCalculateClick = async () => {
        if (handler) {
            try {
                const result = await handler(firstInput, secondInput)
                if (!result) {
                    setOutput('Error!')
                }
                else if (!result.data) {
                    setOutput(result.error)
                } else {
                    setOutput(result.data)
                    dispatch(addResult(result.data))
                }
            } catch (error) {
                console.error("Error in calculation:", error)
                setOutput(error)
            }
        } else {
            setOutput("No handler found for this route")
        }
    }

    if (route?.slug === 'main') {
        return null;
    }

    return <div className='output component output_style'>
        <div className='output__placeholder'>
            <TextField>Значення виразу:</TextField>
            <Button onClick={onCalculateClick}>Обрахувати</Button>
        </div>
        <OutputField value={output} />
    </div>
}