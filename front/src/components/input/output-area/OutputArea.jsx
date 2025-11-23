import '../basic-input/BasicInput.css'
import '../output/OutputField.css'
import './OutputArea.css'

export const OutputArea = ({ value }) => {
    return (
        <textarea
            className='output-field basic-input output-area'
            readOnly
            placeholder='Output'
            value={value}
        />
    );
};
