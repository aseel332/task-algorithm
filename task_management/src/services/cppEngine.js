// src/services/cppEngine.js
import { spawn } from 'child_process';
import path from 'path';
import { fileURLToPath } from 'url';

// Fix __dirname in ES modules
const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

export function runCppEngine(input) {
    return new Promise((resolve, reject) => {
        // Absolute path to your C++ engine
        const enginePath = path.resolve(__dirname, '../../engine/build/engine.exe'); 
        // On Linux/macOS you could just remove .exe

        const cpp = spawn(enginePath, [], { stdio: ['pipe', 'pipe', 'pipe'] });

        let output = '';
        let error = '';

        cpp.stdin.write(JSON.stringify(input));
        cpp.stdin.end();

        cpp.stdout.on('data', (data) => output += data.toString());
        cpp.stderr.on('data', (data) => error += data.toString());

        cpp.on('close', (code) => {
            if (code !== 0) reject(new Error(error));
            else resolve(JSON.parse(output));
        });
    });
}