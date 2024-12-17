import 'dart:convert';
import 'dart:developer';

import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'package:intl/intl.dart';
import '../models/city.dart';
import '../models/constants.dart';
import '../widgets/weather_item.dart';

const String ADAFRUIT_USERNAME = "QliShad";
const String ADAFRUIT_KEY = "aio_kDJX87ON2JZKtWAPS6mFXfqp8tRb";
const String BASE_URL = "https://io.adafruit.com/api/v2";







// Fetch Adafruit Data

class Home extends StatefulWidget {
  const Home({super.key});

  @override
  State<Home> createState() => _HomeState();
}

class _HomeState extends State<Home> {
  Constants myConstants = Constants();

  // initialization
  int temperature = 0;
  int maxTemp = 0;
  String weatherStateName = 'Loading..';
  int windSpeed = 0;
  var currentDate = 'Loading..';
  String imageUrl = '';
  String location = 'London'; //Our default city
  int humidity = 0;
  int windDirection = 0;
  int rainFall = 0;
  int distance = 0;


  //get the cities and selected cities data
  var selectedCities = City.getSelectedCities();
  List<String> cities = [
    'London'
  ]; //the list to hold our selected cities. Deafult is London

  List consolidatedWeatherList = []; //To hold our weather data after api call


// initState Humidity
  @override
  void initState() {
    super.initState();
    fetchAllData();  // Fetch humidity when the widget initializes
  }


  Future<List<dynamic>> fetchAdafruitData(String feedKey) async {
    final url = Uri.parse('$BASE_URL/$ADAFRUIT_USERNAME/feeds/$feedKey/data');
    final response = await http.get(
      url,
      headers: {
        'X-AIO-Key': ADAFRUIT_KEY, // API key for Adafruit IO
        'Content-Type': 'application/json',
      },
    );

    if (response.statusCode == 200) {
      // Parse the JSON data
      final data = jsonDecode(response.body);
      return data; // Return parsed data
    } else {
      throw Exception('Failed to load $feedKey data: ${response.statusCode}');
    }
  }

  Future<void> fetchAllData() async {
    try {
      // Fetch humidity and temperature data in parallel
      final results = await Future.wait([
        fetchAdafruitData("humidity"),
        fetchAdafruitData("temperature"),
        fetchAdafruitData("windspeed"),
        fetchAdafruitData("winddirect"),
        fetchAdafruitData("distance"),
        fetchAdafruitData("waterfall"),

      ]);

      // Extract and parse data
      final humidityData = results[0];
      final temperatureData = results[1];
      final windspeedData = results[2];
      final winddirectionData = results[3];
      final distanceData = results[4];
      final waterfallData = results[5];


      setState(() {
        humidity = double.parse(humidityData[0]['value']).round();
        temperature = double.parse(temperatureData[0]['value']).round();
        windSpeed = double.parse(windspeedData[0]['value']).round();
        windDirection = double.parse(winddirectionData[0]['value']).round();
        distance = double.parse(distanceData[0]['value']).round();
        rainFall = double.parse(waterfallData[0]['value']).round();
      });

      log("Humidity fetched: $humidity");
      log("Temperature fetched: $temperature");
      log("Wind Speed fetched: $windSpeed");
      log("Wind Direction fetched: $windDirection");
      log("Distance fetched: $distance");
      log("Rain Fall fetched: $rainFall");
    } catch (e) {
      log("Error fetching data: $e");
    }
  }

  //Create a shader linear gradient
  final Shader linearGradient = const LinearGradient(
    colors: <Color>[Color(0xffABCFF2), Color(0xff9AC6F3)],
  ).createShader(const Rect.fromLTWH(0.0, 0.0, 200.0, 70.0));


  @override
  Widget build(BuildContext context) {
    //Create a size variable for the media query
    Size size = MediaQuery.of(context).size;


    return Scaffold(
      appBar: AppBar(
        automaticallyImplyLeading: false,
        centerTitle: false,
        titleSpacing: 0,
        backgroundColor: Colors.white,
        elevation: 0.0,
        title: Container(
          padding: const EdgeInsets.symmetric(horizontal: 20),
          width: size.width,
          child: Row(
            mainAxisAlignment: MainAxisAlignment.spaceBetween,
            crossAxisAlignment: CrossAxisAlignment.center,
            children:[
              // Our profile image
              ClipRRect(
                borderRadius: const BorderRadius.all(Radius.circular(10)),
                child: Image.asset(
                  'assets/profile.png',
                  width: 40,
                  height: 40,
                ),
              ),

              // Our location dropdown
              Row(
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  Image.asset(
                    'assets/pin.png',
                    width: 20,
                  ),
                  const SizedBox(
                    width: 4,
                  ),
                  DropdownButtonHideUnderline(child: DropdownButton(
                    value: location,
                    icon: const Icon(Icons.keyboard_arrow_down),
                    items: cities.map((String location){
                      return DropdownMenuItem(
                        value: location,
                        child: Text(location)
                      );
                    }).toList(),
                    onChanged: (String? newValue){
                      setState(() {
                        location = newValue!;
                        // fetchLocation(location);
                        // fetchWeatherData();
                      });
                    }
                  ),
                  )
                ],
              )
            ],
          ),
        ),
      ),
      body:Container(
        padding: const EdgeInsets.all(20),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Text(location, style: const TextStyle(
              fontWeight: FontWeight.bold,
              fontSize: 30.0,
            ),),
            Text(currentDate, style: const TextStyle(
              color: Colors. grey,
              fontSize: 36.0,
            ),),
            const SizedBox(
              height:50,
            ),
            Container(
              width: size.width,
              height: 200,
              decoration: BoxDecoration(
                color: myConstants.primaryColor,
                borderRadius: BorderRadius.circular(15),
                boxShadow: [
                  BoxShadow(
                    color: myConstants.primaryColor.withOpacity(.5),
                    offset: const Offset(0, 25),
                    blurRadius: 10,
                    spreadRadius: -12,
                  )
                ]
              ),
              child: Stack(
                clipBehavior: Clip.none,
                children: [
                Positioned(
                top: -40,
                left: 20,
                child: imageUrl == ''
                    ? const Text('')
                    : Image.asset(
                  'assets/$imageUrl.png',
                  width: 150,
                ),
                ),
                  Positioned(
                    bottom: 30,
                    left: 20,
                    child: Text(
                      weatherStateName,
                      style: const TextStyle(
                        color: Colors.white,
                        fontSize: 20,
                      ),
                    ),
                  ),
                  Positioned(
                      top: 20,
                      right: 20,
                      child: Row(
                      crossAxisAlignment: CrossAxisAlignment.start,
                      children: [
                        Padding(
                          padding: const EdgeInsets.only(top: 4.0),
                          child: Text(
                          temperature.toString(),
                          style: TextStyle(
                          fontSize: 80,
                          fontWeight: FontWeight.bold,
                          foreground: Paint()..shader = linearGradient,
                        ),
                      ),
                  ),
                  Text('o', style: TextStyle(
                      fontSize: 40,
                      fontWeight: FontWeight.bold,
                      foreground: Paint()..shader = linearGradient,
                  ),
                  )
                ], // children
              ),
            ),
          ], // children
        ),
      ),
            const SizedBox(
              height: 50,
            ),
            Container(
              padding: const EdgeInsets.symmetric(horizontal: 10),
              child: Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children:[
                  weatherItem(text: 'Wind Speed', value: temperature, unit: 'km/h', imageUrl: 'assets/windspeed.png'),
                  weatherItem(text: 'Humidity', value: humidity, unit: '%', imageUrl: 'assets/humidity.png'),
                  weatherItem(text: 'Direction', value: windDirection, unit: 'km/h', imageUrl: 'assets/winddirect.jpg'),
                  weatherItem(text: 'Rain Fall', value: rainFall, unit: 'km/h', imageUrl: 'assets/rainfall.png'),
                  weatherItem(text: 'Distance', value: distance, unit: 'km/h', imageUrl: 'assets/distance.png'),

          ],  // children
              ),
            ),
            const SizedBox(height: 50,),
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              crossAxisAlignment: CrossAxisAlignment.center,
              children: [
                const Text(
                  'Today',
                  style: TextStyle(
                    fontWeight: FontWeight.bold,
                    fontSize: 24,
                  ),
                ),
                Text(
                  'Next 7 Days',
                  style: TextStyle(
                      fontWeight: FontWeight.w600,
                      fontSize: 18,
                      color: myConstants.primaryColor),
                ),
              ],
            ),
            const SizedBox(
              height: 20,
            ),
            Expanded(
                child: ListView.builder(
                  scrollDirection: Axis.horizontal,
                  itemCount: consolidatedWeatherList.length,
                    itemBuilder: (BuildContext context, int index){
                      String today = DateTime.now().toString().substring(0, 10);
                      var selectedDay =
                      consolidatedWeatherList[index]['applicable_date'];
                      var futureWeatherName =
                      consolidatedWeatherList[index]['weather_state_name'];
                      var weatherUrl =
                      futureWeatherName.replaceAll(' ', '').toLowerCase();
                      var parsedDate = DateTime.parse(
                          consolidatedWeatherList[index]['applicable_date']);
                      var newDate = DateFormat('EEEE')
                          .format(parsedDate)
                          .substring(0, 3); //format date
                      return Container(
                        padding: EdgeInsets.symmetric(vertical: 20),
                        margin: const EdgeInsets.only(
                            right: 20, bottom: 10, top: 10),
                        width: 80,
                      decoration: BoxDecoration(
                        color: selectedDay == today
                            ? myConstants.primaryColor
                            : Colors.white,
                        borderRadius:
                        const BorderRadius.all(Radius.circular(10)),
                          boxShadow: [
                            BoxShadow(
                              offset: const Offset(0, 1),
                              blurRadius: 5,
                              color: selectedDay == today
                                  ? myConstants.primaryColor
                                  : Colors.black54.withOpacity(.2),
                            ),
                          ]
                      ),
                        child: Column(
                          mainAxisAlignment: MainAxisAlignment.spaceBetween,
                          children: [
                            Text(
                              "${consolidatedWeatherList[index]['the_temp']
                                  .round()}C",
                              style: TextStyle(
                                fontSize: 17,
                                color: selectedDay == today
                                    ? Colors.white : myConstants.primaryColor,
                                fontWeight: FontWeight.w500,
                              ),
                            ),
                            Image.asset(
                              '${'assets/' + weatherUrl}.png',
                              width: 30,
                            ),
                            Text(
                              newDate,
                              style: TextStyle(
                                fontSize: 17,
                                color: selectedDay == today
                                    ? Colors.white
                                    : myConstants.primaryColor,
                                fontWeight: FontWeight.w500,
                              ),
                            )
                          ],
                        ),
                      );
                    }
                ) )
        ], // Children
      ),
    ),
    );
  }
}

