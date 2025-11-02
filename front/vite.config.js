import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import { TanStackRouterVite } from '@tanstack/router-plugin/vite'

export default defineConfig(({ mode }) => {
  return {
    plugins: [TanStackRouterVite(), react()],
    server: {
      host: true, // Allow external access for local development
      port: 3000, // Use a specific port for local development
    },
    build: {
      outDir: 'dist', // Ensure this matches Dockerfile COPY
      sourcemap: mode === 'development', // Optional: Include source maps for debugging in dev
    },
    define: {
      'process.env.VITE_BACKEND_URL': JSON.stringify(
        mode === 'development'
          ? 'http://localhost:8080' // Backend URL during development
          : 'http://consoleapp:8080' // Backend URL in production (Docker internal)
      ),
    },
  }
})