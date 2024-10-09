// src/components/Popup.js
import React from 'react';
import './Popup.css';

const Popup = ({ onClose, children }) => {
  return (
    <div className="popup-overlay">
      <div className="popup-content">
        {children}
        <button className="popup-close" onClick={onClose}>
          <svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="black">
            <path d="m256-200-56-56 224-224-224-224 56-56 224 224 224-224 56 56-224 224 224 224-56 56-224-224-224 224Z"/>
          </svg>
        </button>
      </div>
    </div>
  );
};

export default Popup;
