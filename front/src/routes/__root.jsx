import { createRootRoute, Outlet } from '@tanstack/react-router'
import { TanStackRouterDevtools } from '@tanstack/router-devtools'
import Compose from '../Compose'
import { Searchbar } from '../components/searchbar/Searchbar'
import { Logger } from '../components/logger/Logger'
import { Output } from '../components/output/Output'
import { NotFound } from '../components/not-found/NotFound'

export const Route = createRootRoute({
  component: () => (
    <>
        <Compose >
            <Searchbar />
            <Logger />
            <Output />
            <Outlet />
        </Compose>
    </>
  ),
  errorComponent: NotFound
})