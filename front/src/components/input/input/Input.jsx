import '../basic-input/BasicInput.css'
import './Input.css'
import React from 'react'

export const Input = React.forwardRef((props, ref) => {
    const { className, ...rest } = props;

    return <input className='basic-input input' ref={ref} {...rest} />;
});
