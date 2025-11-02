import { AppLayout } from './components/app-layout/AppLayout'
import { PageLayout } from './components/page-layout/PageLayout'

function Compose({children}) {

  return (
    <PageLayout>
      <AppLayout>
        {children}
      </AppLayout>
    </PageLayout>
  )
}

export default Compose
