import { Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { environment } from '../../environments/environment';
import * as Plotly from 'plotly.js';

// HTML <script type='text/javascript' src="https://cdnjs.cloudflare.com/ajax/libs/proj4js/2.3.6/proj4.js"></script>
// import * as proj4 from 'proj4.js';
// export default proj4;
// (window as any).proj4 = proj4;
import * as Highcharts from 'highcharts/highmaps';

// import * as Highcharts from 'highcharts';
// import MapModule from 'highcharts/modules/map';
// MapModule(Highcharts);
   
@Component({
  selector: 'app-user-profile',
  templateUrl: './user-profile.component.html',
  styleUrls: ['./user-profile.component.css']
})
export class UserProfileComponent implements OnInit {

  title = 'The BoringUI for Woody';
  autoRefresh: boolean;
  refreshInterval: number; // ms

  constructor(private http_cli: HttpClient) {
    console.log(this.title);
    this.refreshInterval = 2000;
    this.autoRefresh = true;
  }

  ngOnInit() {
    Highcharts.setOptions({
      plotOptions: {
        series: {
          animation: false
        }
      }
    });

    this.cities_geo();
    this.city_checkin_heapmap();
  }

  private fetchUserCheckin() {
    /**
    const url = environment.woody_apiserver + '/v1/metrics/user_checkin'
      + '?' + 'gt=' + this.itemClickConf.gt + '&limit=' + this.itemClickConf.limit;
    this.http_cli.get(url)
      .subscribe(rsp => { this.onItemClick(rsp); });
    */
  }

  cities_geo() {
    const layout = {
      title: 'City in Record',
      titlefont: {
        size: 20
      },
      font: {
        family: 'Droid Serif, serif',
        size: 10,
        color: '#000999'
      },
      geo: {
        scope: 'world',
        projection: { type: 'mercator' },
        showcoastlines: false,
        showframe: false,
        showland: true,
        landcolor: 'rgb(220, 220, 220)',
        // showrivers: true,
        showlakes: true,
        lakecolor: 'lightblue',
        showcountries: true,
        // countrycolor: 'rgb(217, 244, 244)',
        countrywidth: 0.5,
        subunitcolor: 'rgb(217, 217, 217)',
        lataxis: { range: [-10] },
        // lonaxis: { range: [-180] },
        resolution: 50
      },
      reversescale: true,
      dragmode: false,
      autosize: false,
      width: 800,
      height: 600
    };

    const data: Plotly.ScatterData[] = [{
      type: 'scattergeo',
      mode: 'markers',
      lat: [-15.615, -15.792110999999998, -16.727004, -20.450997, -25.526997, -35.423001, -36.826002, -38.728998, -41.474996999999995, -23.641002, -29.900996999999997, -33.021, -33.475023, -29.959002, -2.203092, -9.979002000000001, -0.2295, -12.057003, -20.221002, -12.081996, -1.439001, -2.459997, -3.122001, -8.762004, -10.212767999999999, -25.305003, -34.622496000000005, -31.316004, -23.580999, -23.954697, -25.430004, -27.576, -30.040002, -34.92, -12.993003, -19.852002, -20.332998, -22.721571, -22.839002999999998, -2.514996, -3.782997, -5.104998, -5.805999, -7.129998, -8.084997, -9.67689, -10.910997, 29.956383000000002, 29.771828999999997, 21.329001, 53.556003000000004, 51.03, 49.274297999999995, 47.588553000000005, 45.442125, 45.020996999999994, 44.924193, 41.598, 35.489996999999995, 32.761458000000005, 37.810458000000004, 38.566998, 37.795815000000005, 37.308105, 34.000002, 40.692996, 39.578004, 38.99412, 38.638881, 35.114724, 33.508998, 31.779999, 29.094003000000004, 24.156423, 32.763726, 30.279996, 29.429919, 25.677, 21.888, 20.673999, 19.251, 22.243239000000003, 19.854999, 19.532997, 19.048635, 17.975997, 17.062002, 16.743996, 19.185003, 22.151997, 20.583, 20.120004, 19.697004, 19.427049, 19.283004000000002, 18.920997, 10.016001, 9.991997999999999, 9.930474, 9.856997999999999, 9.002880000000001, 13.701410999999998, 13.673997, 20.982996, 18.0333, 17.994996, 17.966925, 18.488997, 18.415998000000002, 3.4569989999999997, 4.630221, 10.983996000000001, 6.240996, 43.720766999999995, 42.898662, 42.39432, 41.390721, 40.497201000000004, 40.044996000000005, 30.449996999999996, 30.33, 27.997353000000004, 25.832124, 43.067943, 43.066665, 42.725997, 41.826546, 39.814002, 39.148011, 36.142002000000005, 35.205822, 34.013996999999996, 33.795999, 39.321882, 38.890908, 37.563003, 36.879290999999995, 35.791002, 40.663962, 39.869163, 43.210467, 40.719996, 40.707864, 40.265001, 40.224996000000004, 39.927555, 42.374997, 41.815998, 41.76, 10.496042999999998, 2.8179990000000004, 10.639737, 18.398997, 14.607432000000001, 0.036, 45.541017, 45.374004, 50.8167, 53.374041000000005, 53.34156, 52.492752, 51.487911, 55.924002, 55.862811, 53.808705, 53.479665000000004, 53.423001, 41.166, 39.471003, 38.729997, 37.373003999999995, 40.44222, 33.605001, 5.558562, 41.357997, 43.781571, 36.866673, 36.819, 44.503002, 41.879996999999996, 41.455998, 40.739004, 39.929004, 35.325998999999996, 35.171001000000004, 30.07791, 30.051513, 37.956294, 38.619, 38.432997, 38.373003000000004, 37.855998, 37.944, 41.681996999999996, 40.984695, 40.629996000000006, 40.155003, 39.647997, 42.707268, 44.430479999999996, 41.066001, 40.773996000000004, 40.766661, 40.195997999999996, 39.783996, 39.419001, 38.763999, 37.878003, 37.776996000000004, 37.764998999999996, 37.220003999999996, 36.892998, 38.355003, 37.585998, 37.159002, 37.069002000000005, 38.730996000000005, 36.999999, 36.797004, 36.233334, 35.106003, 33.883326000000004, 33.833304, 41.292999, 40.984002000000004, 40.913001, 41.020002000000005, 41.001003000000004, 31.9167, 32.045004, 32.042997, 31.949378999999997, 21.543003, 50.13, 48.881997, 48.789999, 51.949998, 51.683337, 51.21, 51.207003, 51.048, 50.964003000000005, 50.837004, 52.387002, 52.373043, 52.100001, 52.075998, 51.92559, 51.987996, 51.240996, 50.852996999999995, 51.354045, 50.942349, 53.570997, 45.074871, 45.473003999999996, 47.401002000000005, 59.331168000000005, 50.105996999999995, 48.202119, 48.140972999999995, 45.424772999999995, 52.516268999999994, 55.719999, 54.708003000000005, 52.244946, 47.514996000000004, 54.789003, 53.899938, 50.448159000000004, 46.466667, 60.19641899999999, 59.41666800000001, 56.88, 59.916663, 57.607002, 57.012003, 56.866671, 56.289671999999996, 48.709998, 47.232, 49.989672, 48.422996999999995, 48.040146, 45.036999, 55.749995999999996, 51.714999, 58.633326000000004, 58.000239, 56.850003, 56.846546999999994, 54.821996999999996, 56.150001, 55.733013, 54.305001000000004, 53.199999, 51.490998, 55.144998, 56.477996999999995, 55.062999, 55.032003, 29.385918, 29.333340000000003, 29.097, 26.333298, 26.262, 26.216666999999998, 26.215956, 26.120997, 26.1, 24.650001, 25.40286, 25.371999, 25.284357, 25.271001000000002, 24.476004, 40.323996, 23.607, 28.666665000000002, 28.568727000000003, 43.255062, 13.061997, 19.077003, 18.535743, 17.395001999999998, 12.974751, 6.927003, 7.080083999999999, 1.483335, 34.378002, 33.949998, 19.906001999999997,
      7.8769979999999995, 5.566662, 4.590999, 3.584997, 5.364, 6.433002, 6.111, 18.786996, 14.344002, 14.016699, 13.848039000000002, 13.750001999999999, 13.588002, 13.536, 13.367997, 13.817997, 16.433001, 14.968998000000001, 17.406999, 3.7999980000000004, 5.325003, 3.15, 3.066696, 1.548999, 2.708001, 2.199996, 1.500003, 0.550998, 1.268856, 6.118002, 10.759185, 25.035093, 31.248, 39.906189000000005, 43.129998, 35.157996000000004, 37.486242, 37.542357, 33.579999, 26.205003, 22.379904, 22.274001000000002, 14.649992999999998, 14.616701999999998, 5.967243, 56.016666, 52.317, 62.01, 48.431996999999996, 43.055001000000004, 38.253996, 35.683002, 35.504577000000005, 35.436996, 35.154999, 35.009001, 34.690149, 34.635996, 35.409996, -33.978996, -1.2699989999999999, -26.178957, -0.954, -6.912, -6.971004, -7.796997, -31.956003000000003, -32.044167, -0.023004, -2.990997, -5.409, -6.166665, -0.5020020000000001, -1.2099959999999998, -3.3280019999999997, -7.399997999999999, -8.589996000000001, -8.70669, -27.453996000000004, -33.88977, -34.811676, -37.852956, -36.903996],
      lon: [-56.093004, -47.897748, -49.255001, -54.615995999999996, -54.622997, -71.659998, -73.054998, -72.575999, -72.95200200000001, -70.398999, -71.24499899999999, -71.555004, -70.647515, -71.332002, -79.907877, -67.812003, -78.524279, -77.14400400000001, -70.148997, -77.045004, -48.498002, -54.610002, -60.014996999999994, -63.906003000000005, -48.360347999999995, -57.621995, -58.449833999999996, -64.179999, -46.622996, -46.309490000000004, -49.284999, -48.618998, -51.208002, -56.169998, -38.481003, -43.909002, -40.413995, -43.455185, -42.881004, -44.300996000000005, -38.589002, -42.802001000000004, -35.210997, -34.866997999999995, -34.914995000000005, -35.74772, -37.060001, -90.098694, -95.40711, -157.861998, -113.508, -114.049998, -122.963067, -122.31665100000001, -122.641686, -93.065004, -93.307787, -93.621996, -97.53000300000001, -117.125496, -122.27147099999999, -121.422996, -122.38009199999999, -121.847454, -118.250001, -111.89199599999999, -105.07899599999999, -94.626566, -90.341982, -90.00032399999999, -112.110003, -106.450002, -110.961999, -110.309526, -96.66369, -97.732998, -98.524575, -100.316996, -102.29000400000001, -103.344003, -103.734999, -97.84262700000001, -90.52599599999999, -96.903, -98.192943, -92.93699699999999, -96.714, -93.10899599999999, -96.122996, -100.98, -100.386999, -98.755002, -101.185002, -99.127575, -99.666702, -99.22100400000001, -84.221, -84.120003, -84.078621, -83.92100400000001, -79.51707900000001, -89.200233, -89.289998, -89.628002, -76.79999699999999, -76.951998, -76.79952, -69.899004, -70.109001, -76.521996, -74.080512, -74.806001, -75.591999, -79.412633, -78.848433, -83.078928, -81.727506, -79.997085, -82.99299599999999, -84.300003, -81.659997, -82.593027, -80.270216, -87.990741, -89.399997, -84.557997, -87.64129799999999, -86.13500400000001, -84.477014, -86.817996, -80.835678, -80.997003, -84.348998, -76.618385, -76.953834, -77.472999, -76.268574, -78.643997, -74.01122099999999, -75.369168, -77.635611, -74.199996, -73.905237, -76.904001, -74.781, -75.21822900000001, -71.10299599999999, -71.42599799999999, -72.702999, -66.89827700000001, -60.663996, -61.49006, -66.068999, -61.075998, -51.048, -73.653534, -75.651003, -1.3332950000000001, -1.462995, -6.257349, -1.8633419999999998, -0.178002, -3.249998, -4.269941, -1.497528, -2.261781, -2.970998, -8.585, -0.367001, -9.129995, -5.970994999999999, -3.690972, -7.631999, -0.200924, 2.159002, 11.207746, 10.199997999999999, 10.166005, 11.333997, 12.52, 31.798999, 31.611997, 32.852998, 33.333003999999995, 33.369004, 31.2508, 31.220956, 23.688378, 27.429004, 27.145, 26.138998, 27.842005, 23.653, 26.561998, 27.516664000000002, 22.799997, 26.414002000000004, 27.883, 23.331871, 26.122969, 29.006002000000002, 29.923002, 30.400003, 29.075003999999996, 30.519, 29.98, 30.539997999999997, 32.482, 29.086003, 30.556998999999998, 28.367002000000003, 30.709, 38.309005, 36.937, 38.797003000000004, 37.389996999999994, 35.479, 35.324002, 34.646005, 36.116677, 33.949999, 35.499997, 35.533297, 36.331003, 37.875997, 38.390005, 40.523004, 39.718, 34.866703, 34.769998, 35.722999, 35.932906, 39.173004999999996, 8.668161, 2.432998, 9.181999000000001, 4.133305, 5.31666, 3.2200029999999997, 4.426003, 3.7359989999999996, 5.483998000000001, 4.367998, 4.632003, 4.894839, 5.112001, 4.281004, 4.485151, 5.923, 6.797998, 5.677002, 7.122439, 6.93487, 10.027998, 7.6664259999999995, 9.189999, 8.533999, 17.991451, 14.456997, 16.320979, 11.542950999999999, 12.370716999999999, 13.327570000000001, 12.549997, 20.503, 21.011878, 19.094005, 32.037003999999996, 27.57556, 30.502108000000003, 30.733335999999998, 24.976702, 24.750001, 24.049999, 30.25, 39.858004, 41.020003, 35.91667, 43.940674, 44.484004, 39.688003, 36.208306, 35.137999, 37.737054, 38.961001, 37.700002000000005, 39.268999, 49.699999, 56.232459999999996, 53.233336, 60.61013199999999, 56.096002, 47.250001, 49.145464000000004, 48.362004999999996, 50.149998, 45.953002000000005, 61.392996999999994, 84.970999, 73.250002, 82.943002, 47.974042, 47.999998, 48.068002, 50.0833, 50.616001000000004, 50.58334, 50.537872, 50.549005, 50.61385, 46.770004, 55.44109, 55.411003, 51.532336, 55.329004000000005, 54.370999, 49.816, 58.588003, 77.216662, 77.216752, 76.912624, 80.247997, 72.826003, 73.852273, 78.485005, 77.58773199999999, 79.848001, 125.613685, 124.849999, 132.445009, 130.933297, 99.833005, 98.38500400000001, 95.333338, 101.076004, 98.676001, 100.311004, 100.189999, 100.361998, 99.000001, 100.560997, 100.533304, 100.519858, 100.516672, 100.603999, 100.274005, 100.987003, 100.063999, 102.836998, 102.10200400000001, 102.79, 103.333303, 103.141, 101.70800200000001, 101.549998, 110.343997, 101.95000300000001, 102.255004, 103.760002, 101.432998, 103.831795, 102.240001, 106.662457, 121.506724, 121.473001, 116.38803700000001, 131.96043999999998, 129.05498799999998, 126.633421, 126.935245, 130.40199099999998, 127.692001, 114.230116, 114.176998, 121.03334199999999, 120.966949, 116.087581, 92.833336, 104.248, 129.830005, 135.127, 141.345991, 140.89101399999998, 139.809007, 139.727215, 139.619998, 136.921006, 135.755002, 135.221212, 135.519004, 136.761994, 18.482004999999997, 36.803998, 28.004310999999998, 100.35199899999999, 107.606998, 110.426005, 110.368999, 115.85300500000001, 115.934572, 109.339003, 104.75700400000001, 105.254002, 106.800004, 117.154, 116.85999699999999, 114.589, 112.684375, 116.137, 115.217272, 153.026002, 151.0282, 138.520828, 145.075105, 174.761002],
      text: ['Cuiaba', 'Brasilia', 'Goiania', 'Campo Grande', 'Puerto Presidente Stroessner', 'Talca', 'Concepcion', 'Temuco', 'Puerto Montt', 'Antofagasta', 'La Serena', 'Valparaiso', 'Santiago', 'Coquimbo', 'Guayaquil', 'Rio Branco', 'Quito', 'Callao', 'Iquique', 'Lima', 'Belem', 'Santarem', 'Manaus', 'Porto Velho', 'Palmas', 'Asuncion', 'Buenos Aires', 'Cordoba', 'Sao Paulo', 'Santos', 'Curitiba', 'Florianopolis', 'Porto Alegre', 'Montevideo', 'Salvador', 'Belo Horizonte', 'Vitoria', 'Rio de Janeiro', 'Niteroi', 'Sao Luis', 'Fortaleza', 'Teresina', 'Natal', 'Joao Pessoa', 'Recife', 'Maceio', 'Aracaju', 'New Orleans', 'Houston', 'Honolulu', 'Edmonton', 'Calgary', 'Vancouver', 'Seattle', 'Portland', 'Saint Paul', 'Minneapolis', 'Des Moines', 'Oklahoma City', 'San Diego', 'Oakland', 'Sacramento', 'San Francisco', 'San Jose', 'Los Angeles', 'Salt Lake City', 'Denver', 'Kansas City', 'St. Louis', 'Memphis', 'Phoenix', 'El Paso', 'Hermosillo', 'La Paz', 'Dallas', 'Austin', 'San Antonio', 'Monterrey', 'Aguascalientes', 'Guadalajara', 'Colima', 'Tampico', 'Campeche', 'Jalapa', 'Puebla', 'Villahermosa', 'Oaxaca', 'Tuxtla Gutierrez', 'Veracruz', 'San Luis Potosi', 'Queretaro', 'Pachuca', 'Morelia', 'Mexico City', 'Toluca', 'Cuernavaca', 'Alajuela', 'Heredia', 'San Jose', 'Cartago', 'Panama', 'San Salvador', 'Nueva San Salvador', 'Merida', 'Halfway Tree', 'Spanish Town', 'Kingston', 'Santo Domingo', 'San Cristobal', 'Cali', 'Bogota', 'Barranquilla', 'Medellin', 'Toronto', 'Buffalo', 'Detroit', 'Cleveland', 'Pittsburgh', 'Columbus', 'Tallahassee', 'Jacksonville', 'Tampa', 'Miami', 'Milwaukee', 'Madison', 'Lansing', 'Chicago', 'Indianapolis', 'Cincinnati', 'Nashville', 'Charlotte', 'Columbia', 'Atlanta', 'Baltimore', 'Washington D.C.', 'Richmond', 'Norfolk', 'Raleigh', 'Brooklyn', 'Chester', 'Rochester', 'Newark', 'New York', 'Harrisburg', 'Trenton', 'Philadelphia', 'Boston', 'Providence', 'Hartford', 'Caracas', 'Boa Vista', 'Port of Spain', 'San Juan', 'Fort-De-France', 'Macapa', 'Montreal', 'Ottawa', 'Fawley', 'Sheffield', 'Dublin', 'Birmingham', 'London', 'Edinburgh', 'Glasgow', 'Leeds', 'Manchester', 'Liverpool', 'Porto', 'Valencia', 'Lisbon', 'Seville', 'Madrid', 'Casablanca', 'Accra', 'Barcelona', 'Florence', "L'Ariana", 'Tunis', 'Bologna', 'Rome', 'Zonguldak', 'Bolu', 'Ankara', 'Kyrenia', 'Nicosia', 'Cairo', 'Giza', 'Piraeus', 'Manisa', 'Izmir', 'Chios', 'Aydin', 'Athens', 'Edirne', 'Tekirdag', 'Thessaloniki', 'Canakkale', 'Balikesir', 'Sofia', 'Bucharest', 'Istanbul', 'Kocaeli', 'Sakarya', 'Bursa', 'Eskisehir', 'Kutahya', 'Afyon', 'Konya', 'Denizli', 'Isparta', 'Mugla', 'Antalya', 'Malatya', 'Kahramanmaras', 'Sanhurfa', 'Aintab', 'Kayseri', 'Seyhan', 'Mersin', 'Antioch', 'Ammochostos', 'Beirut', "B'abda", 'Samsun', 'Ordu', 'Giresun', 'Rize', 'Trabzon', 'Ramla', 'Tel Aviv-Yafo', 'As-Salt', 'Amman', 'Jeddah', 'Frankfurt', 'Paris', 'Stuttgart', 'Europoort', "'s-Hertogenbosch", 'Bruges', 'Antwerpen', 'Gent', 'Hasselt', 'Brussels', 'Haarlem', 'Amsterdam', 'Utrecht', 'The Hague', 'Rotterdam', 'Arnhem', 'Dusseldorf', 'Maastricht', 'Essen', 'Cologne', 'Hamburg', 'Turin', 'Milan', 'Zurich', 'Stockholm', 'Prague', 'Vienna', 'Munich', 'Venice', 'Berlin', 'Copenhagen', 'Kaliningrad', 'Warsaw', 'Budapest', 'Smolensk', 'Minsk', 'Kyiv', 'Odesa', 'Helsinki', 'Tallinn', 'Riga', 'Saint Petersburg', 'Yaroslavl', 'Ivanovo', 'Tver', "Gor'kiy", 'Volgograd', 'Rostov-on-Don', 'Kharkiv', "Dnipropetrovs'k", "Donets'k", 'Krasnodar', 'Moscow', 'Voronezh', 'Vyatka', "Perm'", 'Izevsk', 'Sverdlovsk', 'Ufa', 'Ceboksary', "Kazan'", "Ul'yanovsk", 'Kuybyskev', 'Saratov', 'Chelyabinsk', 'Tomsk', 'Omsk', 'Novosibirsk', 'Kuwait', 'Hawalli', 'Al-Ahmadi', 'Ad Damman', 'Al-Muharraq', 'Manama', 'Jidd Hafs', 'Ar Rifa', 'Sitrah', 'Riyadh', 'Ajman', 'Sharjah', 'Doha', 'Dubai', 'Abu Dhabi', 'Baku', 'Muscat', 'Delhi', 'New Delhi', 'Almaty', 'Chennai', 'Mumbai', 'Pune', 'Hyderabad', 'Bangalore', 'Colombo', 'Davao', 'Manado', 'Hiroshima', 'Shimonoseki', 'Chang Rai', 'Phuket', 'Banda Aceh', 'Ipoh', 'Medan', 'Pinang', 'Kangar', 'Alor Setar', 'Chiang Mai', 'Phra Nakhon Si Ayutthaya', 'Pathum Thani', 'Nonthaburi', 'Bangkok', 'Samut Prakan', 'Samut Sakhon', 'Chon Buri', 'Nakhon Pathom', 'Khon Kaen', 'Nakhon Ratchasima', 'Udon Thani', 'Kuantan New Port', 'Kuala Terengganu', 'Kuala Lumpur', 'Shah Alam', 'Kuching', 'Seremban', 'Melaka', 'Johor Baharu', 'Pekanbaru', 'Singapore', 'Kota Baharu', 'Ho Chi Minh City', 'Taipei', 'Shanghai', 'Beijing', 'Vladivostok', 'Pusan', 'Inch`on', 'Seoul', 'Fukuoka', 'Naha', 'Kowloon', 'Hong Kong', 'Quezon City', 'Manila', 'Kota Kinabalu', 'Krasnoyarsk', 'Irkutsk', 'Yakutsk', 'Khabarovsk', 'Sapporo', 'Sendai', 'Tokyo', 'Kawasaki', 'Yokohama', 'Nagoya', 'Kyoto', 'Kobe', 'Osaka', 'Gifu', 'Cape Town', 'Nairobi', 'Johannesburg', 'Padang', 'Bandung', 'Semarang', 'Yogyakarta', 'Perth', 'Fremantle', 'Pontianak', 'Palembang', 'Tanjungkarang-Telukbetung', 'Jakarta', 'Samarinda', 'Balikpapan', 'Bandjermasin', 'Surabaja', 'Mataram', 'Denpasar', 'Brisbane', 'Sydney', 'Adelaide', 'Melbourne', 'Auckland'],
      // lat: [40.712033033064166, 40.75313016065781, 40.71037756449118, 40.71037756449118, 40.71037756449118, 35.705101088587135, 35.715581120393146, 35.714542173995646, 35.72559198908874, 35.656083091901124],
      // lon: [-74.00699299251195, -73.97621627458902, -74.00755405426025, -74.00755405426025, -74.00755405426025, 139.61959004402158, 139.8003172874451, 139.4800649934587, 139.7766325938853, 139.734045462721],
      // text: ['Coffee Shop', 'Miscellaneous Shop', 'Subway', 'Subway', 'Subway', 'Cosmetics Shop', 'Ramen /  Noodle House', 'Convenience Store', 'Food & Drink Shop', 'Housing Development'],
      name: 'City',
      marker: {
        line: {
          color: '#000000',
          width: 1
        }
      }
    }];
    
    Plotly.plot('container_city_geo', data, layout, {showlink: false});
  }

  /**
   * TODO(zex): Request for city check-in count metrix
   */
  city_checkin_heapmap() {
    const layout = {
      title: 'Global Check-in Event',
      titlefont: {
        size: 20
      },
      font: {
        family: 'Droid Serif, serif',
        size: 10,
        color: '#000999'
      },
      geo: {
        scope: 'world',
        projection: { type: 'mercator' },
        showcoastlines: false,
        showframe: false,
        showlakes: false,
        showcountries: true,
        countrywidth: 0.5,
        lataxis: { range: [-10] },
        // lonaxis: { range: [-180] },
        resolution: 50
      },
      dragmode: false,
      autosize: false,
      width: 800,
      height: 600
    };

    const data: Plotly.ScatterData[] = [{
      type: 'choropleth',
      z: [519,217,334,835,511,633,134,181,960],
      locations: ['Australia', 'South Africa', 'New Zealand', 'Russia', 'Kenya', 'Japan', 'United States', 'Indonesia', 'Paraguay', 'Brazil'],
      locationmode: 'country names',
      text: ['Australia', 'South Africa', 'New Zealand', 'Russia', 'Kenya', 'Japan', 'United States', 'Indonesia', 'Paraguay', 'Brazil'],
      autocolorscale: true,
      reversescale: false,
      name: 'Global Check-in',
      marker: {
        line: {
          color: 'rgb(180,180,180)',
          width: 1
        }
      },
      colorbar: {
        title: "Check-in Count",
        thickness: 10,
        autotick: false
      }
    }];

    Plotly.plot('container_city_checkin', data, layout, {showlink: false});
  }
}
