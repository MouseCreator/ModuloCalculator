import './InfoButton.css'

export const InfoButton = ({ children, onClick, ...props }) => {
    return (
        <button
            className='info-button'
            onClick={onClick}
            {...props}
        >
            {children}
        </button>
    );
};
