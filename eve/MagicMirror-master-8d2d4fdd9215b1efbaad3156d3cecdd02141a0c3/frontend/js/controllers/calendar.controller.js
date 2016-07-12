(function () {
    function calendarController ( $scope, $interval ) {
        $scope.calendarView = 'day';
        $scope.calendarDate = new Date();
        $scope.events = [
          {
            title: 'My event title', // The title of the event
            type: 'info', // The type of the event (determines its color). Can be important, warning, info, inverse, success or special
            startsAt: new Date(), // A javascript date object for when the event starts
            //endsAt: new Date(2014,8,26,15), // Optional - a javascript date object for when the event ends
            incrementsBadgeTotal: true, //If set to false then will not count towards the badge total amount on the month and year view
            allDay: false // set to true to display the event as an all day event on the day view
          }
        ];
        $scope.calendarTitle = "Your Calendar today";
    }

    calendarController.$inject = ['$scope', '$interval'];

    angular.module("mirror").controller('calendarController', calendarController)
})();
