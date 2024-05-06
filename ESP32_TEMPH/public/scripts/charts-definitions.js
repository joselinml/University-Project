window.addEventListener('load', onload);



function onload(event){
  chartT = createTemperatureChart();
  chartpH = createpHChart();
 
}

// Create Temperature Chart
function createTemperatureChart() {
  var chart = new Highcharts.Chart({
    chart:{ 
      renderTo:'chart-temperature',
      type: 'spline' 
    },
    series: [
      {
        name: 'BME280',
        data:[]
      }
    ],
    title: { 
      text: undefined
    },
    plotOptions: {
      line: { 
        animation: false,
        dataLabels: { 
          enabled: true 
        }
      }
    },
    xAxis: {
      title: {
        text:'Hora, minutos y segundos',
      },
      type: 'datetime',
      labels: {
        formatter: function () {
          // Convertir la fecha y hora a la zona horaria de México
          var dateTimeMX = moment.tz(this.value, "America/Mexico_City");
          // Formatear solo la hora
          return dateTimeMX.format('HH:mm:ss');
        }
      }
    },
    
    yAxis: {
      title: { 
        text: 'Temperatura' 
      }
    },
    credits: { 
      enabled: false 
    }
  });
  return chart;
}

// Create Humidity Chart
function createpHChart(){
  var chart = new Highcharts.Chart({
    chart:{ 
      renderTo:'chart-pH',
      type: 'spline'  
    },
    series: [{
      name: 'BME280'
    }],
    title: { 
      text: undefined
    },    
    plotOptions: {
      line: { 
        animation: false,
        dataLabels: { 
          enabled: true 
        }
      },
      series: { 
        color: '#bf9000' 
      }
    },
    xAxis: {
      title: {
        text:'Hora, minutos y segundos',
      },
      type: 'datetime',
      labels: {
        formatter: function () {
          // Convertir la fecha y hora a la zona horaria de México
          var dateTimeMX = moment.tz(this.value, "America/Mexico_City");
          // Formatear solo la hora
          return dateTimeMX.format('HH:mm:ss');
        }
      }
    },
    yAxis: {
      title: { 
        text: 'pH ' 
      }
    },
    
    credits: { 
      enabled: false 
    }
  });
  return chart;
}
