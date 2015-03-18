var macAddress = "00:14:02:11:08:07";

var app = {
    initialize: function() {
        this.bindEvents();
    },
    bindEvents: function() {
        document.addEventListener('deviceready', this.onDeviceReady, false);
    },
    onDeviceReady: function() {
        bluetoothSerial.connect(macAddress, app.onConnect, app.onDisconnect);
    },
    onConnect: function() {
        bluetoothSerial.subscribe("\n", app.onMessage, app.subscribeFailed);
        statusDiv.innerHTML="Connected to " + macAddress + ".";        
    }, 
    onDisconnect: function() {
        alert("Disconnected");
        statusDiv.innerHTML="Disconnected.";
    },
    onMessage: function(data) {

    	var strData= data
    	var intID = 1
    		if (strData.substring(0,5)=='--CAL'){

			   //  		Pebble.sendAppMessage({0: "hello"},
						//     function(message){
						//         console.log('success');
						//     },
						//     function(err){
						//         alert(err);
						//     }
						// );

				cordova.plugins.notification.local.schedule({
				    title: "BigBYTE",
   					 message: "Alarm is Set",
				});
				}

                if (strData.substring(0,5)=='ALARM'){

               //       Pebble.sendAppMessage({0: "hello"},
                        //     function(message){
                        //         console.log('success');
                        //     },
                        //     function(err){
                        //         alert(err);
                        //     }
                        // );

                cordova.plugins.notification.local.schedule({
                    title: "BigBYTE",
                     message: "YOU GOT ONE!!",
                });
                }
			intID=intID+1;


        counter.innerHTML = data;  
        statusDiv.innerHTML= data;      
    },
    subscribeFailed: function() {
        alert("subscribe failed");
    }
//
};
