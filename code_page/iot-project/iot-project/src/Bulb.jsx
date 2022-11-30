import imgOn from "./images/buld-on.png";
import imgOff from "./images/buld-off.png";

export default function Bulb(props) {
  const isActive = props.light;
  console.log(isActive);
  if (isActive) {
    return (
      <>
        <img src={imgOn} id="lightbulb" />
        <h3 id="bulb-text">Encendido</h3>
      </>
    );
  } else {
    return (
      <>
        <img src={imgOff} id="lightbulb" />
        <h3 id="bulb-text">Apagado</h3>
      </>
    );
  }
}
