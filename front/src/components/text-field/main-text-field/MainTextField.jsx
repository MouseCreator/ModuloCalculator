import './MainTextField.css'

export const MainTextField = ({children}) => {
    const [beforeDash, ...restAfterDash] = children.split(' – ');
    const afterDash = restAfterDash.join(' – ');
    return <span className="main-text-field">
            <span className="main-text-before-dash">{beforeDash} – </span>
        {afterDash && <span className="main-text-after-dash">{afterDash}</span>}
        </span>
}