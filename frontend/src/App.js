import React from 'react';
import './App.css';
import CPUForm from './components/CPUForm';

function App() {
    return (
        <div className="App">
            <header className="App-header">
                <h1>CPU Scheduler Simulator</h1>
            </header>
            <main>
                <CPUForm />
            </main>
        </div>
    );
}

export default App;
