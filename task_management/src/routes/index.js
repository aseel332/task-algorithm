// src/routes/index.js
import { Router } from 'express';
import { runCppEngine } from '../services/cppEngine.js';

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