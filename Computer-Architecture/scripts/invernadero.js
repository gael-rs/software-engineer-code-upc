const zonasData = {
    A: {
        producto: "Tomates",
        celsius: { tempOptima: 21, humedad: 60, tempMin: 18, tempMax: 25 },
        fahrenheit: { tempOptima: 70, humedad: 60, tempMin: 64, tempMax: 77 },
    },
    B: {
        producto: "Lechugas",
        celsius: { tempOptima: 16, humedad: 70, tempMin: 14, tempMax: 18 },
        fahrenheit: { tempOptima: 61, humedad: 70, tempMin: 57, tempMax: 64 },
    },
    C: {
        producto: "Pimientos",
        celsius: { tempOptima: 22, humedad: 65, tempMin: 20, tempMax: 24 },
        fahrenheit: { tempOptima: 72, humedad: 65, tempMin: 68, tempMax: 75 },
    },
    D: {
        producto: "Fresas",
        celsius: { tempOptima: 18, humedad: 75, tempMin: 15, tempMax: 20 },
        fahrenheit: { tempOptima: 65, humedad: 75, tempMin: 59, tempMax: 68 },
    },
    E: {
        producto: "Zanahorias",
        celsius: { tempOptima: 20, humedad: 50, tempMin: 17, tempMax: 22 },
        fahrenheit: { tempOptima: 68, humedad: 50, tempMin: 63, tempMax: 72 },
    },
    F: {
        producto: "Espinacas",
        celsius: { tempOptima: 15, humedad: 80, tempMin: 12, tempMax: 17 },
        fahrenheit: { tempOptima: 59, humedad: 80, tempMin: 54, tempMax: 63 },
    },
    G: {
        producto: "Pepinos",
        celsius: { tempOptima: 24, humedad: 65, tempMin: 22, tempMax: 26 },
        fahrenheit: { tempOptima: 75, humedad: 65, tempMin: 72, tempMax: 79 },
    },
    H: {
        producto: "Calabazas",
        celsius: { tempOptima: 19, humedad: 60, tempMin: 16, tempMax: 21 },
        fahrenheit: { tempOptima: 66, humedad: 60, tempMin: 61, tempMax: 70 },
    },
};

const zonas = document.querySelectorAll(".zona");
const tempActual = document.getElementById("temp-actual");
const tempEditable = document.getElementById("editable-temp");
const tempMin = document.getElementById("temp-min");
const tempMax = document.getElementById("temp-max");
const productoNombre = document.getElementById("producto-nombre");
const tempOptima = document.getElementById("temp-optima");
const humedad = document.getElementById("humedad");

let zonaSeleccionada = null;
let unidadSeleccionada = "celsius";

zonas.forEach((zona) => {
    zona.addEventListener("click", () => {
        const zonaId = zona.getAttribute("data-zona");
        actualizarZona(zonaId);
    });
});

function actualizarZona(zonaId) {
    const data = zonasData[zonaId];
    if (!data) return;

    const valores = data[unidadSeleccionada];

    productoNombre.textContent = data.producto;
    tempOptima.textContent = `${valores.tempOptima}°${unidadSeleccionada === "fahrenheit" ? "F" : "C"}`;
    humedad.textContent = `${valores.humedad}%`;

    tempActual.textContent = `${valores.tempOptima}°${unidadSeleccionada === "fahrenheit" ? "F" : "C"}`;
    tempEditable.textContent = `${valores.tempOptima}°${unidadSeleccionada === "fahrenheit" ? "F" : "C"}`;
    tempMin.textContent = `${valores.tempMin}°${unidadSeleccionada === "fahrenheit" ? "F" : "C"}`;
    tempMax.textContent = `${valores.tempMax}°${unidadSeleccionada === "fahrenheit" ? "F" : "C"}`;

    zonas.forEach((z) => z.classList.remove("zona-seleccionada"));
    document.querySelector(`[data-zona="${zonaId}"]`).classList.add("zona-seleccionada");

    zonaSeleccionada = zonaId;
}

document.getElementById("temp-up").addEventListener("click", () => {
    modificarTemperatura(1);
});
document.getElementById("temp-down").addEventListener("click", () => {
    modificarTemperatura(-1);
});

function modificarTemperatura(cambio) {
    if (!zonaSeleccionada) {
        alert("Primero selecciona una zona.");
        return;
    }

    const data = zonasData[zonaSeleccionada][unidadSeleccionada];
    let nuevaTemp = parseInt(tempEditable.textContent);

    nuevaTemp += cambio;

    if (nuevaTemp >= data.tempMin && nuevaTemp <= data.tempMax) {
        tempEditable.textContent = `${nuevaTemp}°${unidadSeleccionada === "fahrenheit" ? "F" : "C"}`;
        tempActual.textContent = `${nuevaTemp}°${unidadSeleccionada === "fahrenheit" ? "F" : "C"}`;
    } else {
        alert("La temperatura está fuera de los límites permitidos.");
    }
}

document.querySelectorAll('input[name="unidad"]').forEach((radio) => {
    radio.addEventListener("change", () => {
        unidadSeleccionada = document.querySelector('input[name="unidad"]:checked').value;

        if (zonaSeleccionada) {
            actualizarZona(zonaSeleccionada);
        }
    });
});


const ctxTemperatura = document.getElementById("graficaTemperatura").getContext("2d");
const ctxHumedad = document.getElementById("graficaHumedad").getContext("2d");

// Datos simulados
const zonasNombres = Object.keys(zonasData);
const temperaturasPromedio = zonasNombres.map(
    (zona) => zonasData[zona].celsius.tempOptima
);
const humedadesPromedio = zonasNombres.map(
    (zona) => zonasData[zona].celsius.humedad
);

// Gráfica de Temperatura
new Chart(ctxTemperatura, {
    type: "bar",
    data: {
        labels: zonasNombres,
        datasets: [
            {
                label: "Temperatura Promedio (°C)",
                data: temperaturasPromedio,
                backgroundColor: "rgba(255, 99, 132, 0.2)",
                borderColor: "rgba(255, 99, 132, 1)",
                borderWidth: 1,
            },
        ],
    },
    options: {
        responsive: true,
        plugins: {
            legend: { display: true },
        },
        scales: {
            y: { beginAtZero: true },
        },
    },
});

// Gráfica de Humedad
new Chart(ctxHumedad, {
    type: "line",
    data: {
        labels: zonasNombres,
        datasets: [
            {
                label: "Humedad Relativa (%)",
                data: humedadesPromedio,
                borderColor: "rgba(54, 162, 235, 1)",
                backgroundColor: "rgba(54, 162, 235, 0.2)",
                tension: 0.3,
            },
        ],
    },
    options: {
        responsive: true,
        plugins: {
            legend: { display: true },
        },
        scales: {
            y: { beginAtZero: true },
        },
    },
});
