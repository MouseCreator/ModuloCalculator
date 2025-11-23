import './OutputField.css'
import '../basic-input/BasicInput.css'

export const OutputField = ({ value }) => {
    return (
        <input
            className='basic-input output-field'
            placeholder='Output'
            readOnly
            value={value}
        />
    );
};
