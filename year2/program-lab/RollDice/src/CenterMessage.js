import React from 'react'
import { Text, View, StyleSheet} from 'react-native'

const CenterMessage = ({ message }) => (
   <View style={StyleSheet.emptyContainer}>
       <Text style={styles.message}>
           {message}
       </Text>
   </View>
)

const styles = StyleSheet.create({
   emptyContainer:{
       padding: 10,
       borderBottomWidth: 2,
       borderBottomColor: 'rgba(0, 0, 0, .5)'
   },
   message: {
       alignSelf: 'center',
       fontSize: 20,
       color: 'rgba(0, 0, 0, .5)'
   }
})

export default CenterMessage