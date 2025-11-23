import { useSelector } from 'react-redux'
import './Navbar.css'
import {InfoButton} from "../button/info-button/InfoButton.jsx"

export const Navbar = () => {
    const route = useSelector(state => state.route.value)

    const openUserGuide = () => {
        const userGuideUrl = 'https://drive.google.com/drive/folders/1QnukZ3SssztUVHJepGlbeGyS5saguEzR?usp=sharing'
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