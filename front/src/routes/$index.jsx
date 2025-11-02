import { createFileRoute } from '@tanstack/react-router'
import { App } from '../components/app/App'
import { CLIENT_ROUTES } from '../../constants/routes'

export const Route = createFileRoute('/$index')({
  component: Index,
})

function Index() {
  return <App />
}
