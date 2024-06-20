# CPU Scheduler Simulator

A web application for simulating CPU scheduling algorithms using React for the frontend and Flask for the backend.

## Features

- Input process details including process ID, arrival time, burst time, and time quantum (for Round Robin algorithm).
- Choose from four CPU scheduling algorithms: FCFS, SJF, Round Robin, and SRTF.
- Display average waiting time, average response time, and average turnaround time based on selected algorithm.
- Simple and interactive user interface.

## Technologies Used

- **Frontend:** React
- **Backend:** Flask
- **Languages:** JavaScript (React), Python (Flask), C++ (algorithms)
- **Styling:** CSS
- **Other:** Axios for API requests, subprocess for executing C++ algorithms

## Installation

1. **Clone the repository**

   ```bash
   git clone https://github.com/kpraveenkumar19/CPUScheduler
   # download it and go that directory 
  

2. **Install dependencies**

   ```bash
    brew install python
    brew install node
    cd frontend
    npm install
    
4. setup environmental var 

    ```bash
    python3 -m venv venv
    source venv/bin/activate
    
5. setting backend
   
   ```bash
   pip install Flask
   pip install flask-cors

6. Run application

    ```bash
    cd backend
    FLASK_APP=app.py flask run
    cd frontend
    npm start
