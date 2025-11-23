import './MainButton.css'

export const MainButton = ({ children, onClick, ...props }) => {
    return (
        <button
            className='main-button'
            onClick={onClick}
            {...props}
        >
            {children}
        </button>
    );
};
