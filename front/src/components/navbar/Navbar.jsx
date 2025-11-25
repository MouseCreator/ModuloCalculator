import { useSelector } from 'react-redux'
import './Navbar.css'
import {InfoButton} from "../button/info-button/InfoButton.jsx"

export const Navbar = () => {
    const route = useSelector(state => state.route.value)

    const openUserGuide = () => {
        const userGuideUrl = 'https://github.com/MouseCreator/ModuloCalculator/blob/main/README.md'
        window.open(userGuideUrl, '_blank')
    }

    return <div className='navbar'>
        <div className="navbar__left">
            <InfoButton onClick={openUserGuide}>
                <span>i</span>
            </InfoButton>
        </div>

        <div className="navbar__center">
            {route.name}
        </div>
    </div>
} 