// src/routes/index.js
import { Router } from 'express';
import { runCppEngine } from '../services/cppEngine.js';
import fs from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';
const router = Router();

router.post('/', async (req, res) => {
    try {
        const input = req.body;
        const output = await runCppEngine(input);
        res.json(output);
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

export default router;

// defining _dirname for ES modules

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const publicPath = path.resolve(__dirname, '../../public');
// getting the route to the public directory to serve the workers.csv file


// Creater workers.csv file using the json data recieved from the workers enfpoint

export const createWorkersCSV = (workers) => {
    const csvHeader = 'id,cost\n';
    const csvRows = workers.map(worker => `${worker.id},${worker.cost}`).join('\n');
    const csvContent = csvHeader + csvRows;
    const filePath = path.join(publicPath, 'workers.csv');
    fs.writeFileSync(filePath, csvContent);
    return filePath;
}

router.post('/workers', (req, res) => {
    try {
        const workers = req.body.workers;
        const filePath = createWorkersCSV(workers);
        res.json({ message: 'CSV file created successfully', filePath });
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

router.get('/workers', (req, res) => {
    try {
        const filePath = path.join(__dirname, 'workers.csv');
        if (fs.existsSync(filePath)) {
            const csvData = fs.readFileSync(filePath, 'utf-8');
            res.setHeader('Content-Type', 'text/csv');
            res.send(csvData);
        } else {
            res.status(404).json({ error: 'CSV file not found' });
        }
    } catch (err) {
        res.status(500).json({ error: err.message });
    }   
});

