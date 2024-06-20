import React from 'react';

const Results = ({ results }) => {
    const [avgWaitTime, avgTurnaroundTime, avgResponseTime] = results.split('\n').map(Number);
    return (
        <div>
            <h2>Results</h2>
            <p>Average Waiting Time: {avgWaitTime}</p>
            <p>Average Turnaround Time: {avgTurnaroundTime}</p>
            <p>Average Response Time: {avgResponseTime}</p>
        </div>
    );
};

export default Results;
