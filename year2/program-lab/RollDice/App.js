import 'react-native-gesture-handler';
import React, { Component } from 'react'
import AbilitiesNavScreen from './src/AbilitiesNavScreen'
import { NavigationContainer } from '@react-navigation/native'
import { createMaterialBottomTabNavigator } from '@react-navigation/material-bottom-tabs';
import AddAbility from './src/AddAbility'
import { StyleSheet, KeyboardAvoidingView } from 'react-native';
import { Platform } from 'react-native';

const Tab = createMaterialBottomTabNavigator()

export default class App extends Component{

 state = {
  abilities: []
 }

 addAbility = (ability) => {
   const abilities = this.state.abilities
   abilities.push(ability)
   this.setState({ abilities })
 }
  addDice = (dice, ability) => {
   const index = this.state.abilities.findIndex(item => {
     return item.id === ability.id
   })
   const chosenAbility = this.state.abilities[index]
   chosenAbility.dices.push(dice)
   const abilities = [
     ...this.state.abilities.slice(0, index),
     chosenAbility,
     ...this.state.abilities.slice(index + 1)
   ]
   this.setState({
    abilities
   })
 }
  render(){
   return(
     <NavigationContainer>
       <KeyboardAvoidingView
         behavior={Platform.OS === "ios" ? "padding" : "height"}
         style={styles.container}>
          <Tab.Navigator
            barStyle={{ backgroundColor: '#661923' }}
            activeColor="#fff"
            inactiveColor="#bbb"
          >
            <Tab.Screen name='Add Ability'>
              {props => <AddAbility {...props}
              addAbility={this.addAbility}/>}
            </Tab.Screen>
            <Tab.Screen name='List Abilities'>
              {props => <AbilitiesNavScreen {...props}
              abilities={this.state.abilities}
              addDice={this.addDice}/>}
            </Tab.Screen>
          </Tab.Navigator>
       </KeyboardAvoidingView>
     </NavigationContainer>
   )
 }
}

const styles = StyleSheet.create({
 container: {
   flex: 1
 },
});