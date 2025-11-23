import './BasicInput.css'

export const BasicInput = (props) => {
    const { className, ...rest} = props

    return <input className='basic-input' {...rest}/>
}