import { createStackNavigator } from '@react-navigation/stack';
import Ability from './Ability';
import Abilities from './Abilities';
import Dice from './Dice';

const AbilitiesNav = createStackNavigator();

const AbilitiesNavScreen = ({ abilities, addDice }) => (
  <AbilitiesNav.Navigator
    screenOptions={{
      headerStyle: {
        backgroundColor: '#661923',
      },
      headerTintColor: '#fff',
      headerTitleStyle: {
        fontWeight: 'bold',
      },
    }}
  >
    <AbilitiesNav.Screen name="Abilities">
      {props => <Abilities {...props} abilities={abilities} />}
    </AbilitiesNav.Screen>
    <AbilitiesNav.Screen
      name="Ability"
      options={({ route }) => ({ title: route.params.ability.ability })}
    >
      {props => <Ability {...props} addDice={addDice} />}
    </AbilitiesNav.Screen>
    <AbilitiesNav.Screen name="Dice" component={Dice} />
  </AbilitiesNav.Navigator>
);

export default AbilitiesNavScreen;