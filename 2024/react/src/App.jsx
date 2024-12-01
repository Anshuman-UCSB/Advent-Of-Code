import Calendar from "./components/Calendar"
import Header from "./components/Header"

function App() {
  return (
    <div className="bg-AOCBackground h-screen w-screen flex flex-col items-center p-10 space-y-10">
      <Header />
      <Calendar />
    </div>
  )
}

export default App
