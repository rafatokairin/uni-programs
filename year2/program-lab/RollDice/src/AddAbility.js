import React from 'react'
import {
 View,
 Text,
 StyleSheet,
 TextInput,
 TouchableOpacity,
 ImageBackground
} from 'react-native'

import * as Random from 'expo-random'

class AddAbility extends React.Component {
 state = {
  ability: '',
 }
 onChangeText = (key, value) => {
   this.setState({ [key]: value })
 }
 submit = () => {
   if (this.state.ability === '') alert('please complete form')
   const ability = {
    ability: this.state.ability,
     id: String(Random.getRandomBytes(8)),
     dices: []
   }
   this.props.addAbility(ability)
   this.setState({
    ability: '',
   })
 }
 render() {
   return (
     <ImageBackground source={require('../img/init.jpg')} style={styles.backgroundImage}>
       <View style={styles.container}>
         <Text style={styles.heading}>Dungeons & Dragons</Text>
         <TextInput
           placeholder='Enter your abilities'
           onChangeText={val => this.onChangeText('ability', val)}
           style={styles.input}
           value={this.state.ability}
         />
         <TouchableOpacity onPress={this.submit}>
           <View style={styles.button}>
             <Text style={styles.buttonText}>Add Ability</Text>
           </View>
         </TouchableOpacity>
       </View>
     </ImageBackground>
   )
 }
}

const styles = StyleSheet.create({
 backgroundImage: {
   flex: 1,
   resizeMode: 'cover',
 },
 button: {
   height: 50,
   backgroundColor: '#800000',
   justifyContent: 'center',
   alignItems: 'center',
   margin: 10
 },
 buttonText: {
   color: 'white',
   fontSize: 18,
 },
 heading: {
   fontWeight: 'bold',
   color: '#e8def8',
   fontSize: 34,
   marginBottom: 10,
   alignSelf: 'center',
 },
 container: {
   flex: 1,
   justifyContent: 'center',
   paddingHorizontal: 20
 },
 input: {
   margin: 10,
   backgroundColor: 'white',
   paddingHorizontal: 8,
   height: 50
 }
})

export default AddAbility