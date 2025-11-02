import { Navbar } from '../navbar/Navbar'
import './PageLayout.css'
import { useSelector } from 'react-redux'

export const PageLayout = ({children}) => {
    const route = useSelector(state => state.route.value)

    const layoutClass = route.slug === 'main' ? 'page-layout-main' : 'page-layout-default'

    return <div className={`page-layout ${layoutClass}`}>
        <Navbar/>
        {children}
    </div>
}