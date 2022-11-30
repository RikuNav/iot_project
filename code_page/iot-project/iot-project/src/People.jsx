import imgOff from './images/people-off.png'
import imgOn from './images/people-on.png'
export default function People(props) {
  const isActive = props.people
  if(isActive){
    return (
      <>
       <img src={imgOn} id='people-image'/>
       <h3 id="people-text">Ocupado</h3>
      </>
    )
  } else{
    return (
    <>
      <img src={imgOff} id='people-image'/>
      <h3 id="people-text">Vacio</h3>
    </>)
  }
}
