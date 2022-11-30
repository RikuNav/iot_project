import "./Home.css";
import Bulb from "../Bulb";
import People from '../People'
const URL = "http://10.25.80.115/4bits?cr=3101"

const getData = async () => {
  const response = await fetch(URL)
  const data = await response.json()
  return data
} 


const data =  await getData()
console.log(data)

const refresh = async() => {
  const resp = await getData()
  console.log(resp[0].luz)
  let bulb = document.querySelector('#lightbulb')
  if(resp[0].luz === 1){
    bulb.src = '/src/images/buld-on.png'
    document.getElementById('bulb-text').innerText="Encendido"
  } else {
    bulb.src = '/src/images/buld-off.png'
    document.getElementById('bulb-text').innerText="Apagado"
  }
  let people = document.querySelector('#people-image')
  if(resp[0].estado === 1){
    people.src = 'src/images/people-on.png'
    document.getElementById('people-text').innerText="Ocupado"
  } else {
    people.src = '/src/images/people-off.png'
    document.getElementById('people-text').innerText="Vacio"
  }
  

}
 setInterval(refresh,1000)



export default function Home() {
  let isActiveLight, isActivePeople
  if(data[0].luz === 1){
    isActiveLight = true
  } else {
    isActiveLight = false
  }
  if(data[0].estado === 1){
    isActivePeople = true
  } else {
    isActivePeople = false
  }

  return (
    <>
    <div className="container">
      <div className="grid">
        <div className="info">
          <h1>Salón 3103</h1>
          <p>Edificio: 3</p>
          <p>Capacidad: 30 personas</p>
          <p>Tipo: Laboratorio</p>
        </div>
        <div className="people">
          <People people={isActivePeople}/>
        </div>
        <div className="bulb">
          <Bulb light={isActiveLight}/>
        </div>
      </div>
    </div>

    </>
  );
}
