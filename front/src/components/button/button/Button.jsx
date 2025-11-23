import './Button.css'

export const Button = ({ children, onClick, ...props }) => {
    return (
        <button
            className='custom-button'
            onClick={onClick}
            {...props}
        >
            {children}
        </button>
    );
};
