import { useSelector, useDispatch } from 'react-redux'
import { Button } from '../button/button/Button.jsx'
import { OutputArea } from '../input/output-area/OutputArea'
import { TextField } from '../text-field/text-field/TextField.jsx'
import './Logger.css'
import { clearHistory } from '../../store/historySlice'

export const Logger = () => {
    const route = useSelector(state => state.route.value)
    const dispatch = useDispatch()
    const log = useSelector(state => state.history.log)

    const handleClear = () => {
        dispatch(clearHistory())
    }

    if (route?.slug === 'main') {
        return null;
    }

    return <div className='logger component logger__style'>
        <div className='logger__placeholder'>
            <TextField>Log list</TextField>
            <Button onClick={handleClear}>Очистити</Button>
        </div>
        <OutputArea
            value={log.length > 0 ? log.join('\n') : 'Історія порожня'}
        />
    </div>
}