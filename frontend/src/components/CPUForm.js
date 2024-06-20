import React, { useState } from 'react';
import axios from 'axios';
import Results from './Results';

const CPUForm = () => {
    const [numProcesses, setNumProcesses] = useState(1);
    const [processes, setProcesses] = useState([{ pid: '', arrival_time: '', burst_time: '' }]);
    const [algorithm, setAlgorithm] = useState('fcfs');
    const [timeQuantum, setTimeQuantum] = useState('');
    const [results, setResults] = useState(null);

    const handleAddProcess = () => {
        setProcesses([...processes, { pid: '', arrival_time: '', burst_time: '' }]);
    };

    const handleChangeProcess = (index, e) => {
        const newProcesses = [...processes];
        newProcesses[index][e.target.name] = e.target.value;
        setProcesses(newProcesses);
    };

    const handleSubmit = async (e) => {
        e.preventDefault();
        const response = await axios.post('http://127.0.0.1:5000/run_algorithm', {
            num_processes: numProcesses,
            processes,
            algorithm,
            time_quantum: timeQuantum,
        });
        setResults(response.data.output);
    };

    return (
        <div>
            <form onSubmit={handleSubmit}>
                <label>
                    Number of Processes:
                    <input
                        type="number"
                        value={numProcesses}
                        onChange={(e) => setNumProcesses(e.target.value)}
                    />
                </label>
                {processes.map((process, index) => (
                    <div key={index}>
                        <label>
                            Process ID:
                            <input
                                type="text"
                                name="pid"
                                value={process.pid}
                                onChange={(e) => handleChangeProcess(index, e)}
                            />
                        </label>
                        <label>
                            Arrival Time:
                            <input
                                type="text"
                                name="arrival_time"
                                value={process.arrival_time}
                                onChange={(e) => handleChangeProcess(index, e)}
                            />
                        </label>
                        <label>
                            Burst Time:
                            <input
                                type="text"
                                name="burst_time"
                                value={process.burst_time}
                                onChange={(e) => handleChangeProcess(index, e)}
                            />
                        </label>
                    </div>
                ))}
                <button type="button" onClick={handleAddProcess}>
                    Add Process
                </button>
                <label>
                    Algorithm:
                    <select value={algorithm} onChange={(e) => setAlgorithm(e.target.value)}>
                        <option value="fcfs">First-Come, First-Served</option>
                        <option value="sjf">Shortest Job First</option>
                        <option value="rr">Round Robin</option>
                        <option value="srtf">Shortest Remaining Time First</option>
                    </select>
                </label>
                {algorithm === 'rr' && (
                    <label>
                        Time Quantum:
                        <input
                            type="text"
                            value={timeQuantum}
                            onChange={(e) => setTimeQuantum(e.target.value)}
                        />
                    </label>
                )}
                <button type="submit">Run Algorithm</button>
            </form>
            {results && <Results results={results} />}
        </div>
    );
};

export default CPUForm;
