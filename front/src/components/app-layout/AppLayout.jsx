import { Navbar } from '../navbar/Navbar'
import { useSelector } from 'react-redux'
import './AppLayout.css'

export const AppLayout = ({children}) => {
    const route = useSelector(state => state.route.value)

    const layoutClass = route.slug === 'main' ? 'app-layout-main' : 'app-layout-default'

    return <div className={`app-layout ${layoutClass}`}>
        {children}
    </div>
}