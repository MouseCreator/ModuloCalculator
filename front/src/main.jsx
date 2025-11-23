import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import './index.css'
import { RouterProvider, createRouter } from '@tanstack/react-router'
import { routeTree } from './routeTree.gen'
import { store } from './store/store.js'
import { Provider } from 'react-redux'

const router = createRouter({ routeTree, })

createRoot(document.getElementById('root')).render(
  <StrictMode>
     <Provider store={store}>
        <RouterProvider router={router} />
     </Provider>
  </StrictMode>,
)
