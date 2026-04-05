// src/app.js
import express from 'express';
import routes from './routes/index.js';

const app = express();

// Middleware
app.use(express.json()); // parse JSON requests

// Routes
app.use('/', routes);

export default app;